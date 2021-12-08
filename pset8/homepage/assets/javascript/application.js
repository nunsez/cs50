import templates from './templates.js'

document.addEventListener('DOMContentLoaded', () => {
    const pageName = document.head.querySelector('meta[name="page"]').content
    templates.initHeader(pageName)
    templates.initFooter()
    templates.initPets(pageName)
    setTimeout(() => templates.initSecret(), 5000)
})
