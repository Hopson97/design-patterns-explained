"use strict";

const UserModel = require('../models/user.model')
const helper = require("./controller_helper");

const router = helper.controllerRouter();
const render = helper.makeRenderer("users");

router.get('/sign_up', (_, response) => {
    render(response, 'sign_up');
});

router.get('/sign_in', (_, response) => {
    render(response, 'sign_in');
});

router.get('/sign_out', (_, response) => {
    response.cookie("user", {
        expires: Date.now()
    });
    response.redirect("/");
});

router.post('/sign_up', async (request, response) => {
    const email = request.body.email;
    const name = request.body.name;
    const pass = request.body.password;

    if (await UserModel.userExists(email)) {
        response.redirect("/");
    } else {
        const user = await UserModel.create(email, name, pass);
        response.cookie("user", user.id)
        response.redirect("/");
    }
});

router.post('/sign_in', async (request, response, next) => {
    const email = request.body.email;
    const pass = request.body.password;
    const user = await UserModel.findBy("email", email);
    if (user && pass === user.password) {
        response.cookie("user", user.id);
        response.redirect("/");
    } else {
        response.locals.errors.push("Incorrect username or password.")
        response.redirect("/users/sign_in");
    }
});


module.exports = {
    router: router
}