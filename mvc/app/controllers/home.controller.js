"use strict";

const helper = require("./controller_helper");
const PostModel = require('../models/post.model');

const router = helper.controllerRouter();

// Home Controller Action: 
// Renders the home page
router.get('/', async (_, response) => {
    response.locals.posts = await PostModel.all();
    response.render('pages/index');
});

module.exports = {
    router: router
}