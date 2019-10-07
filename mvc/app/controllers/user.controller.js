"use strict";

const helper = require("./controller_helper");

const router = helper.controllerRouter();
const render = helper.makeRenderer("users");

router.get('/sign_up/', (request, response) => {
    render(response, 'sign_up')
});

router.post('/sign_up/', (request, response) => {
    console.log(request.body.username);

    response.render("/");
});


module.exports = {
    router: router
}