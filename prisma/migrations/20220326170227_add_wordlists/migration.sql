/*
  Warnings:

  - Added the required column `name` to the `WordLists` table without a default value. This is not possible if the table is not empty.
  - Added the required column `words` to the `WordLists` table without a default value. This is not possible if the table is not empty.

*/
-- RedefineTables
PRAGMA foreign_keys=OFF;
CREATE TABLE "new_WordLists" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "name" TEXT NOT NULL,
    "words" TEXT NOT NULL
);
INSERT INTO "new_WordLists" ("id") SELECT "id" FROM "WordLists";
DROP TABLE "WordLists";
ALTER TABLE "new_WordLists" RENAME TO "WordLists";
PRAGMA foreign_key_check;
PRAGMA foreign_keys=ON;
