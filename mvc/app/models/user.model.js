"use strict"

const db = require('./database');
const Model = require('./model');
con

class UserModel extends Model {
    constructor() {
        super("users")
    }

    async currentUser (cookie) {
        if(cookie.user) {
            return await super.find(cookie.user);
        }
        return null;
    }

    async userExists(email) {
        return await super.findBy("email", email);
    }

    async create(email, name, password)  {
        return await db.insertIntoUsers(email, name, password);
    }
}

module.exports = new UserModel();