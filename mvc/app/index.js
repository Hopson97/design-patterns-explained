const express = require("express")
const ejslayout = require("express-ejs-layouts");
const path = require('path');

const cookieParser = require('cookie-parser');
const bodyParser = require('body-parser');

const commentsController = require('./controllers/comment.controller');
const postsController = require('./controllers/post.controller');
const usersController = require('./controllers/user.controller');
const homeController  = require('./controllers/home.controller');

const UserModel = require('./models/user.model');

const app = express();

/*
 	Set up the application middleware
*/
//Front end
app.use(ejslayout);
app.set(`view engine`, `ejs`);
app.set(`views`, path.join(__dirname, "/../public/views/"));
app.use(express.static(`./public/`));

//Parsers
app.use(cookieParser());
app.use(bodyParser.urlencoded({extended: true}));

//Middleware 
const auth = express.Router();
auth.use( async (request, response, next) => {
	response.locals.current_user = await UserModel.currentUser(request.cookies)
	response.locals.errors = [];
	await next();
});

app.use(auth);

//Controllers
app.use("/comments/", 	commentsController.router);
app.use("/posts/", 		postsController.router);
app.use("/users/", 		usersController.router);
app.use(				homeController.router);

//Start the server
app.listen(8080, _ => {
	console.log(`Server started.`);
	console.log(`Current Time: ${new Date()}\n`);
});