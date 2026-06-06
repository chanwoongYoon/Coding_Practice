const express = require("express");
const app = express();

const sqlite = require("sqlite");
const sqlite3 = require("sqlite3");

async function getDatabase(){
    return db = await sqlite.open({
        filename : './database.db',
        driver : sqlite3.Database
    });
}

async function make_Table(table_name,db){
    const makeTable = `
        CREATE TABLE IF NOT EXISTS ${table_name} (
            name TEXT,
            age INTEGER,
            gender TEXT
        )
    `
    await db.exec(makeTable);
}

const PORT = 3000;

app.get('/', async (req, res) => {
    const db = await getDatabase();
    
    // await를 사용하여 비동기 함수가 완료될 때까지 기다림
    await make_Table('Author', db);
    await make_Table('Customers', db);
    
    console.log('DB 및 테이블 생성 완료');

    await db.close();
    res.send("DB 및 테이블 생성 성공"); // 응답을 보내 브라우저 로딩 종료
});

app.listen(PORT,()=>{
    console.log(`http://localhost:${PORT}`)
});