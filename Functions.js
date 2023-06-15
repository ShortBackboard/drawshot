//在界面加载图片
function setPriImgSource() {
    priImg.source = ""  //先清除已有的qurl，类似刷新操作
    priImg.source = "image://mypixmap/"
}

//截取屏幕
function captureScreen(){
    root.visible = false;
    cutTimer.start();
}

//选择截图区域
function selectArea(){
    fullScreen();
}
