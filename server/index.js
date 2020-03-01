const express = require("express");

const app = express();

const path = require("path");

app.use(express.static(path.join(__dirname,"/../","public/"),{
    setHeaders:(res,path,stats) =>{
        if(path.endsWith(".wasm")){
            res.set("Content-Type","application/wasm")
        } 
    }
}));

app.listen(8112, () => {
    console.log(`App listening on port 8112!`);
});
