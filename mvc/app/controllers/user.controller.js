"use strict";

const UserModel = require('../models/user.model')
const helper = require("./controller_helper");

const router = helper.controllerRouter();
const render = helper.makeRenderer("users");

router.get('/sign_up/', (request, response) => {
    render(response, 'sign_up');
});

router.get('/sign_in/', (request, response) => {
    render(response, 'sign_in');
});

router.get('/sign_out/', (request, response) => {
    response.cookie("user", {expires: Date.now()});
    response.redirect("/");
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

router.post('/sign_in/', (request, response) => {
    render(response, 'sign_in');
});


module.exports = {
    router: router
}