# Spresense-LCD-Board
## LCD board for Spresense
Spresenseの拡張ボードにスタックするLCDボードです
<br>
## 組み立て完成写真
![](DOC/IMG_4691.jpeg)<br><br>

## LCDボードとSpresense拡張ボード
![](DOC/IMG_4679.jpeg)<br><br>


## 使用するLCD
![](/DOC/IMG_4674.jpeg)

写真左）3.5 インチタッチスクリーン MHS TFT LCD モジュール画面ディスプレイ<br>
写真右）GeeekPi 3.5インチ320 * 480モニタータッチパネルRaspberry Pi LCD　　
<br>
<br>
<br>

## ボードの組み立て
### - ピンヘッダー５組
### - プルアップ抵抗（10kΩ）
### - 電源シュートジャンパーを半田付け
### - カメラをカメラマウンターに取り付け<br><br>
![](DOC/IMG_4697.jpeg)
<br>
<br>

### カメラマウンター<br>
![](DOC/Spresense_CAMERA_BASE7.jpg)<br>
### [カメラマウンター] DOC/SPRESENSE CAMERA BASE7.stl <br>
### [カメラマウンター　TinkCad](https://www.tinkercad.com/things/2FAODkR43Zt-spresense-camera-base7)
<br><br>

## ビルド
1. フォルダ（camera_apitest2）をArduinoスケッチフォルダーにコピー
2. ボードパッケージは "2.6.0" を使用します（3.xでは問題あり）
3. Memory:1536KBを選択
4. ライブラリーに "LovyanGFX" と "XPT2046_Touchscreen" をインストール
5. ビルドしてアップロード

<br><br>
## 使用方法
- オリジナルはSpresenseのサンプルスケッチ->camera->camera_apitest.inoです<br>
  LovyanGFXでプレビュー表示するする処理を追加<br>
  タッチパネル読み取り処理を追加<br>
  オリジナルにあるSerialターミナルでのメニュー操作はそのままです<br>
  （写真の解像度、ISO感度などの設定、撮影画像のSDへの保存などができます）<br>
- タッチパネルによる写真撮影処理を追加
- 撮影した写真のサムネイル表示処理を追加（最新の5枚まで表示）

  
  
