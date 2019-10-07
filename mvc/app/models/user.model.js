"use strict"

const db = require('./database');

module.exports = {
    currentUser: () => {

    },

    userExists: async email => {
        let exists = false;
        return await db.find("users", "email", email);
    },

    create: async(email, name, password) => {
        await db.insertIntoUsers(email, name, password);
    }
};
