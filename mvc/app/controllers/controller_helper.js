"use strict"

const express = require("express");

module.exports = {
    controllerRouter: () => {
        const router = express.Router();
        router.use(express.static(`./public/`));
        return router;
    },

    makeRenderer: (route) => {
        return (response, page) => {
            response.render(`pages/${route}/${page}.ejs`);
        }
    }
}