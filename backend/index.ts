import express from "express";
import { Prisma, PrismaClient } from "@prisma/client";
import crypto from "crypto";
import WebSocket from "ws";

const server = new WebSocket.Server({
  port: 8080,
});

let sockets: any = [];
server.on("connection", (socket) => {
  console.log("user connected");

  sockets.push(socket);

  socket.on("message", function (msg) {
    sockets.forEach((s: any) => s.send(msg));
  });

  // When a socket closes, or disconnects, remove it from the array.
  socket.on("close", function () {
    sockets = sockets.filter((s: any) => s !== socket);
  });
});

const prisma = new PrismaClient();
const app = express();

// Middleware for handling JSON
app.use(express.json());

app.post("/", async (req, res) => {
  console.log(req.body);
  res.send({
    test: "aaaaaa"
  });
});

app.post("/create", async (req, res) => {
  console.log(req.body)
  if (req.body.words && Array.isArray(req.body.words)) {
    console.log("here");
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
      data: result,
    });
  } else {
    res.send({
      status: "err",
      data: {},
    });
  }
});

app.post("/join", async (req, res) => {
  const game = await prisma.games.findFirst({
    where: {
      isRunning: true,
      gameCode: req.body.gameCode,
    },
  });

  if (game) {
    res.send({
      status: "ok",
      words: game.words,
    });
  } else {
    res.send({
      status: "err",
      words: "",
    });
  }
});

app.post("/checkwin", async (req, res) => {
  const game = await prisma.games.findFirst({
    where: {
      isRunning: true,
      gameCode: req.body.gameCode,
    },
  });

  const winningWords = game?.winningWords.split(";");

  if (
    winningWords?.every((word: string) => req.body.words.includes(word)) &&
    winningWords.length > 0
  ) {
    res.send({
      status: "ok",
      won: true,
    });
  } else {
    res.send({
      status: "ok",
      won: false,
    });
  }
});

app.post("/changecorrect", async (req, res) => {
  const game = await prisma.games.findFirst({
    where: {
      isRunning: true,
      gameCode: req.body.gameCode,
    },
  });

  let winningWords: string[] = []
  if (game && game.words.split(";").includes(req.body.word) && req.body.word.length > 0) {
    winningWords = game.winningWords.split(";");

    if (!winningWords?.includes(req.body.word))
      winningWords.push(req.body.word);

    else
      winningWords.splice(winningWords.indexOf(req.body.word), 1);

    const result = await prisma.games.update({
      where: {
        gameCode: req.body.gameCode
      },
      data: {
        winningWords: winningWords.join(";")
      }
    });

    res.send({
      status: "ok",
      winningWords: result.winningWords
    })
  }
  else {
    res.send({
      status: "err",
      winningWords: ""
    })
  }
})

app.listen(3000, () => {
  console.log("listening on *:3000");
});
