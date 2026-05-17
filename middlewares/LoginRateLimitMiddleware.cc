#include "LoginRateLimitMiddleware.h"

namespace
{
// ODR-uses DrObject<LoginRateLimitMiddleware>::alloc_, whose ctor registers the
// class with DrClassMap so ADD_METHOD_TO(..., "LoginRateLimitMiddleware") resolves.
[[maybe_unused]] const std::string &loginRateLimitMiddlewareDrRegistration =
    LoginRateLimitMiddleware::classTypeName();
}
