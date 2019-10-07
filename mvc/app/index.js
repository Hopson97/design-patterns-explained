const express = require("express")
const ejslayout = require("express-ejs-layouts");
const path = require('path');

const cookieParser = require('cookie-parser');
const bodyParser = require('body-parser');

const comments = require('./controllers/comment.controller');
const posts = require('./controllers/post.controller');
const users = require('./controllers/user.controller');



const app = express();

/*
 	Set up the application middleware
*/
//Front end
app.use(express.static(`./public/`));
app.use(ejslayout);
app.set(`view engine`, `ejs`);
app.set(`views`, path.join(__dirname, "/../public/views/"));

//Parsers
app.use(cookieParser());
app.use(bodyParser.urlencoded({extended: true}));

//Controllers
app.use("/comments/", comments.router);
app.use("/posts/", posts.router);
app.use("/users/", users.router);

/*
 	Basic routes
*/
app.get(`/`, (request, response) => {
	const cookie = request.cookies;
	console.log(cookie);
	response.locals = {
		title: "Home",
		signed_in: false
	};
	response.render("pages/index.ejs")
});

//Start the server
app.listen(8080, _ => {
	console.log(`Server started.`);
	console.log(`Current Time: ${new Date()}\n`);
});