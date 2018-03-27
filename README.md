# mmdpipy
 mmdpi を使って Python から pmd, pmx モデルを動かすことのできるライブラリです。
 
 # インストール手順
apt-get install libboost-dev libboost-python-dev<br>
pip install pyopengl<br>
<br>
git clone https://github.com/shirobu2400/mmdpi<br>
cd mmdpi<br>
cmake .. (-Dpi=on でラズベリーパイ上 -Dbullet=on で物理演算込み)<br>
make -j N (N はコンパイルスレッド数)<br>
make install 
cd ..<br>
<br>
make<br>

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
