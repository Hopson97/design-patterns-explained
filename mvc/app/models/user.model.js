"use strict"

const db = require('./database');

module.exports = {
    currentUser: async (cookie) => {
        if(cookie.user) {
            return await db.find("users", "id", cookie.user);
        }
        return null;
    },

    userExists: async email => {
        let exists = false;
        return await db.find("users", "email", email);
    },

    create: async(email, name, password) => {
        return await db.insertIntoUsers(email, name, password);
    }
};
