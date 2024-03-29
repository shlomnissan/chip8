const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");

module.exports = {
    devServer: {
        port: 3000
    },
    output: {
        path: __dirname + "/dist/",
        filename: "index.js"
    },
    module: {
        rules: [
            {
                test: /\.js$/,
                exclude: /node_modules/,
                use: {
                    loader: "babel-loader",
                    options: {
                        presets: ["@babel/preset-env"],
                        plugins: ["@babel/plugin-syntax-dynamic-import", "@babel/transform-runtime"]
                    }
                }
            },
            {
                test: /\.less$/,
                use: [MiniCssExtractPlugin.loader, "css-loader", "less-loader"],
            },
            {
                test: /\.(gif|png|jpe?g|svg|woff)$/i,
                use: ["file-loader", {
                    loader: "image-webpack-loader"
                }],
            }
        ]
    },
    plugins: [
        new MiniCssExtractPlugin({
            filename: "style.css",
        }),
        new HtmlWebpackPlugin({
            template: "src/index.html",
            templateParameters: {
                src: process.env.WEBPACK_DEV_SERVER ? "src/chip8/chip8.js" : "chip8.js"
            }
        })
    ]
};
