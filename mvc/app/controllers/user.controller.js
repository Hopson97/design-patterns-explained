"use strict";

const UserModel = require('../models/user.model')
const helper = require("./controller_helper");

const router = helper.controllerRouter();
const render = helper.makeRenderer("users");

router.get('/sign_up/', (request, response) => {
    render(response, 'sign_up')
});

router.post('/sign_up/', async (request, response) => {
    const email = request.body.username;
    const name = request.body.name;
    const pass = request.body.password;

    if(await UserModel.userExists(email)) {
        response.redirect("/");
    }
    else {
        UserModel.create(email, name, pass);
        response.redirect("/");
    }
});

module.exports = {
    router: router
}