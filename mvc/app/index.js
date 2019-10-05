const express = require("express")
const ejslayout = require("express-ejs-layouts");
const path = require('path');

const comments = require('./controllers/comment.controller');
const posts = require('./controllers/post.controller');
const users = require('./controllers/user.controller');

//Set up the application
const app = express();
app.use(express.static(`./public/`));
app.use(ejslayout);
app.set(`view engine`, `ejs`);
app.set(`views`, path.join(__dirname, "/../public/views/"));

app.use("/comments/", comments.router);
app.use("/posts/", posts.router);
app.use("/users/", users.router);

//Routes
app.get(`/`, (request, response) => {
	response.locals = {
		title: "Home"
	};
	response.render("pages/index.ejs")
});

//Start the server
app.listen(8080, _ => {
	console.log(`Server started.`);
	console.log(`Current Time: ${new Date()}\n`);
});