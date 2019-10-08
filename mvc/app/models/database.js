"use strict"

const jsonfile = require('jsonfile')
const fileName = "bloggy.json";

const lastId = (json, table) => {
    const record = json[table][json[table].length - 1];
    return record? record.id : 0;
}


//Fake "JSON" databse because cba for sql
module.exports = {
    find: async (table, value, find) => {
        const json = await jsonfile.readFile(fileName);
        for (const record of json[table]) {
            if (record[value] == find) {
                return record;
            }
        }
        return null;
    },

    insertIntoUsers: async (email, name, password) => {
        const json = await jsonfile.readFile(fileName);
        const users = json.users;
        const user = {
            id: lastId(json, 'users') + 1,
            email,
            name,
            password
        };
        users.push(user);

        json.users = users;
        await jsonfile.writeFile(fileName, json);
        return user;
    }
}