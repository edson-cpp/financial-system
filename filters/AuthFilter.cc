#include "AuthFilter.h"

void AuthFilter::doFilter(
    const HttpRequestPtr &req,
    FilterCallback &&fcb,
    FilterChainCallback &&fccb)
{
    auto session = req->session();

    if (!session || !session->find("user_id"))
    {
        req->session()->insert("redirect_after_login", req->path());
        
        auto resp = HttpResponse::newRedirectionResponse("/login");

        fcb(resp);
        return;
    }

    fccb();
}
