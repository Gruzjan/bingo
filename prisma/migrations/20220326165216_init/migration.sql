-- CreateTable
CREATE TABLE "Games" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "isRuuning" BOOLEAN NOT NULL,
    "gameCode" TEXT NOT NULL
);

-- CreateTable
CREATE TABLE "WordLists" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT
);

-- CreateTable
CREATE TABLE "SavedBoards" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "gameId" INTEGER NOT NULL,
    "name" TEXT NOT NULL,
    "board" TEXT NOT NULL,
    CONSTRAINT "SavedBoards_gameId_fkey" FOREIGN KEY ("gameId") REFERENCES "Games" ("id") ON DELETE RESTRICT ON UPDATE CASCADE
);

-- CreateIndex
CREATE UNIQUE INDEX "SavedBoards_gameId_key" ON "SavedBoards"("gameId");
