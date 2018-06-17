# mmdpipy
 mmdpi を使って Python から pmd, pmx モデルを動かすことのできるライブラリです。
 
 # インストール手順
apt-get install libboost-dev libboost-python-dev python-opengl<br>
pip install pyopengl<br>
<br>
mmdpi をインストール済み
<br>
cmake<br>
<br>
RaspberryPi に一応対応しています.(多分..)<br>
RaspberryPi のレガシードライバには非対応(黒い画面が出るだけ.)<br>

# メソッド群
mmdpipy.load(model_name) => モデル名でモデル読み込み<br>
mmdpipy.vmdload(model_name) => モーション名でモーション読み込み<br>
mmdpipy.draw() => 表示<br>
mmdpipy.setBone(bone_name, matrix) => ボーン名に対応するボーンの姿勢行列を matrix で上書き<br>
mmdpipy.bonePos(bone_name, x, y, x) => ボーン名に対応するボーンをx,y,z の位置に平行移動<br>
mmdpipy.boneRotX(bone_name, rotx) => ボーン名に対応するボーンをx軸回転<br>
mmdpipy.boneRotY(bone_name, roty) => ボーン名に対応するボーンをy軸回転<br>
mmdpipy.boneRotZ(bone_name, rotz) => ボーン名に対応するボーンをz軸回転<br>
mmdpipy.setProjectionMatrix(width, height) => スクリーンの幅と高さで投射行列を生成する<br>
mmdpipy.step01() => モーションを一ステップ進める<br>

# 注意事項
プロタイプです。
動作の保証はありません。

