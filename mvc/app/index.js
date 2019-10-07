const express = require("express")
const ejslayout = require("express-ejs-layouts");
const path = require('path');

const cookieParser = require('cookie-parser');
const bodyParser = require('body-parser');

const comments = require('./controllers/comment.controller');
const posts = require('./controllers/post.controller');
const users = require('./controllers/user.controller');

const UserModel = require('./models/user.model');

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

//Middleware 
const auth = express.Router();
auth.use( async (request, response, next) => {
	response.locals.current_user = await UserModel.currentUser(request.cookies)
	console.log("I am called!");
	await next();
});

app.use(auth);

//Controllers
app.use("/comments/", comments.router);
app.use("/posts/", posts.router);
app.use("/users/", users.router);



/*
 	Basic routes
*/
app.get(`/`, async (request, response) => {
	response.locals.title = "Home";
	response.render("pages/index.ejs")
});

//Start the server
app.listen(8080, _ => {
	console.log(`Server started.`);
	console.log(`Current Time: ${new Date()}\n`);
});