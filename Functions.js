//在界面加载图片
function setPriImgSource() {
    priImg.source = ""  //先清除已有的qurl，类似刷新操作
    priImg.source = "image://mypixmap/"+Math.random()   //？？？//必须加上后面的Math.random()才能刷新图片
}

//截取屏幕
function captureScreen(){
    root.visible = false;
    cutTimer.interval += arguments[0];
    cutTimer.start();
}

//截图选中区域
function cutArea(x,y,w,h){
    shotFullScreen(x+1,y+1,w-3,h-3);
    setPriImgSource();
}

//加载备截取截图
function selectImg(){
    selectWin.sImg.source = ""
    selectWin.sImg.source = "image://mypixmap/"+Math.random()
}
