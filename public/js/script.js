document.getElementById('open_btn').addEventListener('click', function () {
    document.getElementById('sidebar').classList.toggle('open-sidebar');
});

async function loadPage(url) {
    try {
        const response = await fetch(url);
        const html = await response.text();

        const parser = new DOMParser();
        const doc = parser.parseFromString(html, 'text/html');

        const newContent = doc.querySelector('#page-content');

        if (newContent) {
            document.querySelector('#content-area').innerHTML = newContent.innerHTML;
        }
    } catch (error) {
        console.error('Error loading page:', error);
    }
}

function loadPageFromUrl() {
    const params = new URLSearchParams(window.location.search);
    const page = params.get('page');

    if (page === 'register') {
        loadPage('/register/content');
    }
}

document.querySelectorAll('[data-page]').forEach(link => {
    link.addEventListener('click', function (e) {
        e.preventDefault();

        const url = this.getAttribute('data-page');

        const pageName = url.split('/')[1];

        history.pushState({}, '', `/dashboard?page=${pageName}`);

        loadPage(url);
    });
});

window.addEventListener('DOMContentLoaded', () => {
    loadPageFromUrl();
});
