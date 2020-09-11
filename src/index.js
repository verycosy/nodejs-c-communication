const net = require("net");

const server = net.createServer((client) => {
  console.log("Client connected");
  client.on("end", () => {
    console.log("Client disconnected");
  });

  client.on("data", (data) => {
    const len = data.byteLength;

    const i = data.indexOf(0x00);
    const t = data.slice(0, i);

    // console.log(len, data);
    console.log(data);
    const tag = t;

    console.log(data.slice(20, 24).readInt8(0));
    console.log(data.slice(24, 28).readInt8(0));

    // console.log(tag.byteLength);
    console.log(tag.toString("utf-8"));
  });
});

server.on("error", (err) => {
  throw err;
});

server.listen("/tmp/echo", () => {
  console.log("Server bound 8124");
});
