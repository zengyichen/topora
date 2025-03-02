## 使用方式

使用 Visual Studio 2022 编译得到 topora.exe。

运行交互界面，手动输入参数：

```powershell
topora.exe
```

通过文件直接输入参数：

```powershell
topora.exe [filename]
```

## 构建规则

#### TO 型

1. 将 z 轴 $[0, 1]$ 等分为 $sliceNum$ 份，分别建立垂直于 z 轴的平面。
2. 在第 $i$ 个平面，以 $(0, 0, z_i)$ 为中心，$radius_i$ 为半径画多边形顶点，边数为 $edgeNum$。仅 $z =0, 1$ 处多边形连边。
3. 将第 $i$ 个平面旋转 $angleOffset$ 度。对于相邻层，本层第 $i$ 个顶点与下一层 $(i + pointOffset)\mod edgeNum$ 相连。

#### PO 型

1. 在 x-y 平面的 $[-xRange, xRange]\times[-yRange, yRange]$ 区域作 $1\times 1$ 网格。

2. 每个网格的 z 坐标按如下公式求出：
   $$
   z(x, y) = (x2Coef)x^2 + (y2Coef)y^2 + (xyCoef)xy + (xCoef)x + (yCoef)y
   $$

#### RA 型

构建的是二维图像，不考虑 z 轴。

1. 将圆周等分为 $sliceNum$ 份。

2. 对于每个角度 $\theta$ 作一对应点，其极坐标 $(\theta, l)$ 中 $l$ 按如下公式求出：
   $$
   l(\theta) = (sinCoef)\sin((sinArg)\theta) + (cosCoef)\cos((cosArg)\theta) + base
   $$
   
3. 连接相邻点。

