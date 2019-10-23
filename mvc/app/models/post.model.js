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
            const user = await UserModel.find(post.userId);
            post.user = user.name;
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

    async postsBy(userId) {
        const posts = await super.all();
        return posts.filter(post => post.userId == userId);
    }
}

module.exports = new PostsModel();
