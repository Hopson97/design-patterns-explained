"use strict";

const helper = require("./controller_helper");

const router = helper.controllerRouter();

/**
 * Controller Action: 
 *  Get the home page
 */
router.get('/', (_, response) => {
    response.render('pages/index.ejs')
});

module.exports = {
    router: router
}