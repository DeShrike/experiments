// npm install webpack webpack-cli --save-dev
// npm install svg-inline-loader --save-dev
// npm install css-loader --save-dev
// npm install style-loader --save-dev
// npm install babel-loader --save-dev

// npm install html-webpack-plugin --save-dev
// npm install webpack-dev-server --save-dev


// const HtmlWebpackPlugin = require("html-webpack-plugin");

const webpack = require("webpack");
const path = require('path');

module.exports = {
   entry: "./index.js",
   module: {
      rules: [
//         { test: /\.svg$/, use: "svg-inline-loader" }
//         { test: /\.css$/, use: [ "style-loader", "css-loader" ] }
         { test: /\.(js)$/, use: "babel-loader" }
      ]
   },
   plugins: [
//      new HtmlWebpackPlugin(),
      new webpack.EnvironmentPlugin({
         "NODE_ENV": "production"
      })
   ],
   output: {
      path: path.resolve(__dirname, "dist"),
      filename: "index_bundle.js"
   },
   mode: process.env.NODE_ENV === "production" ? "production" : "development"
}
