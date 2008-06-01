# coding: mbcs

from todpython import *
import wx

#-------------------------------------------------------------------------------
class SceneViewPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, wx.NewId(), style=wx.NO_FULL_REPAINT_ON_RESIZE)
        self.sceneView = newobj('SceneView')
        self.sceneView.setSceneRootPath('/usr/scene')
        self.sceneView.setWindowId(self.GetHandle())
        
        self.Bind(wx.EVT_PAINT, self.OnPaint, id=self.GetId())
        self.Bind(wx.EVT_MOTION, self.OnMotion, id=self.GetId())
        self.Bind(wx.EVT_KEY_DOWN, self.OnKeyDown, id=self.GetId())
        
    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        dc.SetBackgroundMode(wx.TRANSPARENT)
        self.sceneView.render()
        
    def OnMotion(self, event):
        x = event.GetX()
        y = event.GetY()
        if event.AltDown():
            if event.LeftIsDown():
                delta_x = self.prev[0] - x
                delta_y = y - self.prev[1]
                self.sceneView.viewEulerRotationX((float)(delta_y) / 100)
                self.sceneView.viewEulerRotationY(-(float)(delta_x) / 100)
                self.sceneView.render()        
            if event.RightIsDown():
                delta_x = self.prev[0] - x
                delta_y = self.prev[1] - y
                self.sceneView.moveForward((float)(delta_y) / 100)
                self.sceneView.moveLeft((float)(delta_x) / 100)
                self.sceneView.render()
        self.prev = (x, y)
    
    def OnKeyDown(self, event):
        kc = event.GetKeyCode()        
        if kc == wx.WXK_UP or kc == 87:
            self.sceneView.moveForward(1)
        if kc == wx.WXK_DOWN or kc == 83:
            self.sceneView.moveForward(-1)
        if kc == wx.WXK_LEFT or kc == 65:
            self.sceneView.moveLeft(1)
        if kc == wx.WXK_RIGHT or kc == 68:
            self.sceneView.moveRight(1)
        self.sceneView.render() 

#-------------------------------------------------------------------------------
class SceneView(wx.aui.AuiNotebook):
    def __init__(self, parent):
        wx.aui.AuiNotebook.__init__(self, parent, style=wx.aui.AUI_NB_DEFAULT_STYLE | wx.aui.wx.NO_BORDER | wx.aui.AUI_NB_WINDOWLIST_BUTTON)
        
    def addViewPanel(self, title):
        self.AddPage(SceneViewPanel(self), title)
