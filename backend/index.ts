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

app.get("/", async (req, res) => {
  console.log(req.body);
  res.send({
    test: "aaaaaa"
  });
})

app.post("/", async (req, res) => {
  console.log(req.body);
  res.send({
    test: "aaaaaa"
  });
});

app.post("/create", async (req, res) => {
  console.log("connection");
  console.log(req.body)
  if (req.body.words && Array.isArray(req.body.words)) {
    console.log("here");

    // Remove ";" in words and join them with ";"
    // as a separator
    const wordsCleaned = req.body.words
      .map((word: string) => word.replace(";", ""))
      .join(";");

    // Create new game instance in the database
    const result = await prisma.games.create({
      data: {
        isRunning: true,
        gameCode: req.body.gameCode,
        words: wordsCleaned,
        size: req.body.size,
        freeTile: req.body.freeTile
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
  console.log("join");
  console.log(req.body);
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
  console.log("checking win");
  const game = await prisma.games.findUnique({
    where: {
      gameCode: req.body.gameCode,
    }
  });

  const winningWords = game?.winningWords.split(";");
  const userWords = req.body.words.split(";");
  if (game) {
    console.log("Winning words:")
    console.log(game.winningWords.split(";"));
  }
  console.log("User words:");
  console.log(userWords);

  if (
    winningWords &&
    userWords?.every((word: string) => winningWords.includes(word)) &&
    winningWords.length > 4
  ) {
    res.send({
      status: "ok",
      won: 1,
    });
  } else {
    res.send({
      status: "ok",
      won: 0,
    });
  }
});

app.post("/changecorrect", async (req, res) => {
  console.log("changing correctness");
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

    let finalWords = winningWords.join(";")
    
    const result = await prisma.games.update({
      where: {
        gameCode: req.body.gameCode
      },
      data: {
        winningWords: finalWords
      }
    });

    console.log(result);

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
