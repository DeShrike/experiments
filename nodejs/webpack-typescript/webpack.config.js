// npm install webpack webpack-cli --save-dev
// npm install svg-inline-loader --save-dev
// npm install css-loader --save-dev
// npm install style-loader --save-dev
// npm install ts-loader --save-dev

// npm install html-webpack-plugin --save-dev
// npm install webpack-dev-server --save-dev

// const HtmlWebpackPlugin = require("html-webpack-plugin");

const webpack = require("webpack");
const path = require('path');

module.exports = {
   devtool: "eval-source-map",
   entry: path.resolve(__dirname, "./src/index.ts"),
   module: {
      rules: [
//         { test: /\.svg$/, use: "svg-inline-loader" }
//         { test: /\.css$/, use: [ "style-loader", "css-loader" ] }
//         { test: /\.(js)$/, use: "babel-loader" },
         { test: /\.ts$/, use: "ts-loader", include: [ path.resolve(__dirname, "src")] }
      ]
   },
   plugins: [
//      new HtmlWebpackPlugin(),
      new webpack.EnvironmentPlugin({
         "NODE_ENV": "production"
      })
   ],
   resolve: {
      extensions: [".ts", ".js"],
   },
   output: {
      path: path.resolve(__dirname, "dist"),
      filename: "bundle.js",
      publicPath: 'dist'
   },
   mode: "production"
   // mode: process.env.NODE_ENV === "production" ? "production" : "development"
}
