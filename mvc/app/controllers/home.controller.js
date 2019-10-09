"use strict";

const helper = require("./controller_helper");

const router = helper.controllerRouter();

// Home Controller Action: 
// Renders the home page
router.get('/', (_, response) => {
    response.render('pages/index')
});

module.exports = {
    router: router
}