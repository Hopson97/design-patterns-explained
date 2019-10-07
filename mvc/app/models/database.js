"use strict"

const jsonfile = require('jsonfile')
const fileName = "bloggy.json";

const lastId = (json, table) => json[table][json[table].length - 1].id;


//Fake "JSON" databse because cba for sql
module.exports = {
    find: async (table, value, find) => {
        const json = await jsonfile.readFile(fileName);
        for (const record of json[table]) {
            if(record[value] === find) {
                return record;
            }
        }
        return null;
    },

    insertIntoUsers: async(email, name, password) => {
        const json = await jsonfile.readFile(fileName);
        console.log(await lastId(json, 'users'));

        const users = json.users;
        users.push({
            id: lastId(json, 'users') + 1,
            email,
            name,
            password
        });

        json.users = users;
        await jsonfile.writeFile(fileName, json);

        
    }
}