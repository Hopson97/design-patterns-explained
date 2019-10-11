"use strict"

const jsonfile = require('jsonfile')
const fileName = "bloggy.json";

const lastId = (json, table) => {
    const record = json[table][json[table].length - 1];
    return record? record.id : 0;
}

async function insert(tableName, data) {
    const json = await jsonfile.readFile(fileName);
    const table = json[tableName];

    console.log("Inserting:", data)

    data.id = lastId(json, tableName) + 1;
    table.push(data);

    json[tableName] = table;
    await jsonfile.writeFile(fileName, json);
    return data;
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
        return insert('users', {
            email,
            name,
            password
        });
    },

    insertIntoPosts: async (title, content, date, userId) => {
        return insert('posts', {
            title,
            content,
            date,
            userId
        });
    },

    getAll: async (table) => {
        const json = await jsonfile.readFile(fileName);
        return json[table];
    }
}