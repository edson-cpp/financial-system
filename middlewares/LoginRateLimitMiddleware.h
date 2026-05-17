#pragma once

//#include <drogon/HttpMiddleware.h>
#include <drogon/drogon.h>
#include <unordered_map>
#include <chrono>
#include <mutex>

using namespace drogon;

class LoginRateLimitMiddleware
    : public HttpMiddleware<LoginRateLimitMiddleware>
{
  public:
    struct AttemptData
    {
        int attempts = 0;

        std::chrono::steady_clock::time_point firstAttempt;
    };

    inline static std::unordered_map<
        std::string,
        AttemptData>
        loginAttempts;

    inline static std::mutex attemptsMutex;

    static constexpr int MAX_ATTEMPTS = 5;

    static constexpr int BLOCK_MINUTES = 15;

    void invoke(
        const HttpRequestPtr &req,
        MiddlewareNextCallback &&next,
        MiddlewareCallback &&callback)
    {
        std::string ip =
            req->peerAddr().toIp();

        auto now =
            std::chrono::steady_clock::now();

        {
            std::lock_guard<std::mutex> lock(
                attemptsMutex);

            auto &data =
                loginAttempts[ip];

            // First attempt
            if (data.attempts == 0)
            {
                data.firstAttempt = now;
            }

            auto elapsed =
                std::chrono::duration_cast<
                    std::chrono::minutes>(
                    now - data.firstAttempt)
                    .count();

            // Reset after expiration
            if (elapsed >= BLOCK_MINUTES)
            {
                data.attempts = 0;
                data.firstAttempt = now;
            }

            // Block request
            if (data.attempts >= MAX_ATTEMPTS)
            {
                auto resp =
                    HttpResponse::newHttpResponse();

                resp->setStatusCode(
                    k429TooManyRequests);

                resp->setBody(
                    "Too many login attempts. Try again later.");

                callback(resp);
                return;
            }

            // Increment attempt count
            data.attempts++;
        }

        next([callback = std::move(callback)]
            (const HttpResponsePtr &resp)
        {
            callback(resp);
        });
    }

    // Call this after successful login
    static void resetAttempts(
        const std::string &ip)
    {
        std::lock_guard<std::mutex> lock(
            attemptsMutex);

        loginAttempts.erase(ip);
    }
};