using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

public class Utils
{
    public static Point GetControlLocation(Control control)
    {
        if (control.Parent != null)
        {
            // 컨트롤이 부모 컨테이너에 속한 경우 위치를 상대적으로 계산
            return control.Location;
        }
        else
        {
            // 컨트롤이 부모 컨테이너에 속하지 않은 경우 위치를 절대적으로 계산
            Point locationOnScreen = control.PointToScreen(Point.Empty);
            return control.Parent.PointToClient(locationOnScreen);
        }
    }
    public static Size GetControlSize(Control control)
    {
        return control.Size;
    }
}
