import content from './content.js'

const getHeader = (pageName) => {
    const pageList = content.pages.reduce((acc, { id, href, title }) => `${acc}\
        <li class="nav-item">\
            <a class="nav-link${pageName === id ? ' active' : ''}" data-page="${id}" href="${href}">${title}</a>\
        </li>`, '')

     return `\
        <div id="header" class="container">
            <nav class="navbar navbar-expand-lg navbar-light bg-light">
                <div class="container-fluid">
                <span class="navbar-brand">Nunsez</span>
                <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                    <span class="navbar-toggler-icon"></span>
                </button>
                <div class="collapse navbar-collapse" id="navbarNav">
                    <ul class="navbar-nav">${pageList}</ul>
                </div>
                </div>
            </nav>
        </div>`
}

const getFooter = () => '\
    <p>Alexander Mandrikov &copy; Apache-2.0</p>\
    <p><a href="https://github.com/nunsez/cs50" target="_blank" rel="noreferrer noopener">Source Code</a></p>'

const getPetCard = ({ breed, src, text }) => `\
    <div class="card" style="width: 18rem;">
        <img src="${src}" class="card-img-top" alt="${breed}">
        <div class="card-body">
            <h5 class="card-title">${breed}</h5>
            <p class="card-text">${text}</p>
          </div>
    </div>`

const getSecret = () => `\
    <div class="modal fade" id="secret" tabindex="-1" aria-labelledby="modalLabel" aria-hidden="true">
        <div class="modal-dialog">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="modalLabel">The secret was found.</h5>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                </div>
                <div class="modal-body">Congratulations! You found the secret!</div>
                <div class="modal-footer"></div>
            </div>
        </div>
    </div>`

function initSecret() {
    const pageName = document.head.querySelector('meta[name="page"]').content
    const trigger = document.querySelector('h1 span')

    if (pageName !== 'main' || !trigger) {
        return;
    }

    const main = document.querySelector('main')
    const secret = document.createElement('div')

    trigger.dataset.bsToggle= 'modal'
    trigger.dataset.bsTarget = '#secret'

    main.append(secret)
    secret.outerHTML = getSecret()
}

function initHeader(pageName) {
    const header = document.body.querySelector('header')
    header.innerHTML = getHeader(pageName)
}

function initFooter() {
    const footer = document.querySelector('footer')
    footer.innerHTML = getFooter()
}

function initPets(pageName) {
    const petList = content[pageName]

    if (!petList) {
        return;
    }

    const container = document.querySelector('#pets')

    petList.forEach((pet) => {
        const petCard = document.createElement('div')
        petCard.innerHTML = getPetCard(pet)
        container.append(petCard)
    })
}

export default {
    initHeader, initFooter, initPets, initSecret,
}
