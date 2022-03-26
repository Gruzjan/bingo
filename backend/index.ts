import express from "express";
import { PrismaClient } from "@prisma/client";

const prisma = new PrismaClient();
const app = express();
 
app.get("/", async (req, res) => {
  res.send("Hello World");
  const newWordlist = await prisma.wordLists.create({
      data: {
          name: "Lysy",
          words: "krzesla;dzieci;slychac klucze;"
      }
  })
  const queryWordlists = await prisma.wordLists.findMany()
  console.log(queryWordlists);
});
 
app.listen(3000);
console.log("Backend started...");