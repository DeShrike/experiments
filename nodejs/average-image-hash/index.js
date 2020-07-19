const fs = require("fs");
const sharp = require("sharp");

async function averageHash(filePath, hashSize = 8) {
  const buffer = await fs.promises.readFile(filePath);

  const resizedBuffer = await sharp(buffer)
    .resize({ width: hashSize, height: hashSize })
    .ensureAlpha()
    //.greyScale()
    // .extractChannel(3)
    .toColourspace("b-w")
    .raw()
    .toBuffer();

  const pixels = [];

  for (let y = 0; y < hashSize; y++) {
    for (let x = 0; x < hashSize; x++) {
      const start = y * hashSize + x * 4;
      const r = resizedBuffer[start];
      const g = resizedBuffer[start + 1];
      const b = resizedBuffer[start + 2];
      const a = resizedBuffer[start + 3];
      const value = parseInt(( r + g + b ) / 12);

    }
  }

}


averageHash("./janefonda1.png");
// averageHash("./janefonda2.png");

