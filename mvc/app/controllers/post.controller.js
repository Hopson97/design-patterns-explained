"use strict";

const PostsModel = require('../models/post.model');
const UsersModel = require('../models/user.model')
const helper = require("./controller_helper");

const router = helper.controllerRouter();
const render = helper.makeRenderer("users");

router.post('/new', (request, response) => {
    PostsModel.create(
        request.body.blog_title, 
        request.body.blog_content,
        UsersModel.currentUser(request.cookies)
    );
    response.redirect('/');
});

module.exports = {
    router: router
}