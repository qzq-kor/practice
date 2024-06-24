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
            // ��Ʈ���� �θ� �����̳ʿ� ���� ��� ��ġ�� ��������� ���
            return control.Location;
        }
        else
        {
            // ��Ʈ���� �θ� �����̳ʿ� ������ ���� ��� ��ġ�� ���������� ���
            Point locationOnScreen = control.PointToScreen(Point.Empty);
            return control.Parent.PointToClient(locationOnScreen);
        }
    }
    public static Size GetControlSize(Control control)
    {
        return control.Size;
    }
}
