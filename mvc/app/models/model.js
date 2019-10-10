"use strict";

const db = require('./database');

module.exports = class Model {
    constructor(name) {
        this.name = name;
    }

    async find(id) {
        return await db.find(this.name, "id", id);
    }

    async findBy(table, value) {
        return await db.find(this.name, table, value);
    }

    async all() {
        return await db.getAll(this.name);
    }
}