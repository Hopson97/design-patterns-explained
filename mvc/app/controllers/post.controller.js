"use strict";

const PostsModel = require('../models/post.model');
const UsersModel = require('../models/user.model')
const helper = require("./controller_helper");

const router = helper.controllerRouter();
const render = helper.makeRenderer("users");

router.post('/new', async (request, response) => {
    const user = await UsersModel.currentUser(request.cookies);
    await PostsModel.create(
        request.body.blog_title, 
        request.body.blog_content,
        user
    );
    response.redirect('/');
});

module.exports = {
    router: router
}