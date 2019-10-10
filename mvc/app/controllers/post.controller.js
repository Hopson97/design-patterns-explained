"use strict";

const express = require('express');

const router = express.Router();
router.use(express.static(`./public/`));

router.post('/new', (request, response) => {
    render(response, 'sign_up');
});

module.exports = {
    router: router
}