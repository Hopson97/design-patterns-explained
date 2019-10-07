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
        const user = await UserModel.create(email, name, pass);
        response.cookie("user", user.id)
        response.redirect("/");
    }
});

router.get('/sign_out/', async (request, response) => {
    response.cookie("user", {expires: Date.now()});
    response.redirect("/");
});

module.exports = {
    router: router
}