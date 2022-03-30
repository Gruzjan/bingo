import express from "express";
import { Prisma, PrismaClient } from "@prisma/client";
import crypto from "crypto";

const prisma = new PrismaClient();
const app = express();

// Middleware for handling JSON
app.use(express.json());

app.get("/", async (req, res) => {
  res.send("Hello World");
});

app.post("/create", async (req, res) => {
  if (req.body.words && Array.isArray(req.body.words)) {
    // Generate a game code
    let code = crypto.randomBytes(4).toString("hex").toUpperCase();
    // Check if it already exists
    let uniqueCode = await prisma.games.findMany({
      where: {
        isRunning: true,
        gameCode: code,
      },
    });

    // Generate the code as long as it's unique
    while (uniqueCode.length) {
      code = crypto.randomBytes(4).toString("hex").toUpperCase();
      uniqueCode = await prisma.games.findMany({
        where: {
          isRunning: true,
          gameCode: code,
        },
      });
    }

    // Remove ";" in words and join them with ";"
    // as a separator
    const wordsCleaned = req.body.words
      .map((word: string) => word.replace(";", ""))
      .join(";");

    // Create new game instance in the database
    const result = await prisma.games.create({
      data: {
        isRunning: true,
        gameCode: code,
        words: wordsCleaned,
      },
    });

    res.send({
        status: "ok",
        data: result
    });
  } else {
    res.send({
      status: "err",
      data: {}
    });
  }
});

app.get("/join", async (req, res) => {});

app.listen(3000);
console.log("Backend started...");
