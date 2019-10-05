const express = require("express")
const ejslayout = require("express-ejs-layouts");
const path = require('path');

//Set up the application
const app = express();
app.use(express.static(`./public/`));
app.use(ejslayout);
app.set(`view engine`, `ejs`);
app.set(`views`, path.join(__dirname, "/../public/views/"));

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