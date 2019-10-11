"use strict"

const db = require('./database');
const Model = require('./model');
const UserModel = require('./user.model');

class PostsModel extends Model {
    constructor() {
        super("posts")
    }

    async all() {
        const posts = await super.all();
        for (const post of posts) {
            post.user = await UserModel.find(post.userId);
        }
        return posts;
    }

    async create(title, content, user) {
        return db.insertIntoPosts(
            title,
            content,
            new Date().toLocaleString(),
            user.id
        );
    }
}

module.exports = new PostsModel();
