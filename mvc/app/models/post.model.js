"use strict"

const db = require('./database');
const Model = require('./model');

class PostsModel extends Model {
    constructor() {
        super("posts")
    }

    async create(title, content, user) {
        return db.insertIntoPosts(
            title,
            content,
            new Date().now,
            user.id
        );
    }
}

module.exports = new PostsModel();