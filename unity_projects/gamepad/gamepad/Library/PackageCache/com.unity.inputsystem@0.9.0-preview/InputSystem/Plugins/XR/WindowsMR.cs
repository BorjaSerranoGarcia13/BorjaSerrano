using UnityEngine.InputSystem.Controls;
using UnityEngine.InputSystem.Layouts;

namespace UnityEngine.InputSystem.XR
{
    /// <summary>
    /// A Windows Mixed Reality XR headset.
    /// </summary>
    [InputControlLayout]
    public class WMRHMD : XRHMD
    {
        public IntegerControl trackingState { get; private set; }
        public ButtonControl isTracked { get; private set; }
        public Vector3Control devicePosition { get; private set; }
        public QuaternionControl deviceRotation { get; private set; }
        public Vector3Control leftEyePosition { get; private set; }
        public QuaternionControl leftEyeRotation { get; private set; }
        public Vector3Control rightEyePosition { get; private set; }
        public QuaternionControl rightEyeRotation { get; private set; }
        public Vector3Control centerEyePosition { get; private set; }
        public QuaternionControl centerEyeRotation { get; private set; }


        protected override void FinishSetup(InputDeviceBuilder builder)
        {
            if (builder == null)
                throw new System.ArgumentNullException(nameof(builder));

            base.FinishSetup(builder);

            trackingState = builder.GetControl<IntegerControl>("trackingState");
            isTracked = builder.GetControl<ButtonControl>("isTracked");
            devicePosition = builder.GetControl<Vector3Control>("devicePosition");
            deviceRotation = builder.GetControl<QuaternionControl>("deviceRotation");
            leftEyePosition = builder.GetControl<Vector3Control>("leftEyePosition");
            leftEyeRotation = builder.GetControl<QuaternionControl>("leftEyeRotation");
            rightEyePosition = builder.GetControl<Vector3Control>("rightEyePosition");
            rightEyeRotation = builder.GetControl<QuaternionControl>("rightEyeRotation");
            centerEyePosition = builder.GetControl<Vector3Control>("centerEyePosition");
            centerEyeRotation = builder.GetControl<QuaternionControl>("centerEyeRotation");
        }
    }

    /// <summary>
    /// A Windows Mixed Reality XR controller.
    /// </summary>
    [InputControlLayout(commonUsages = new[] { "LeftHand", "RightHand" })]
    public class WMRSpatialController : XRControllerWithRumble
    {
        [InputControl(aliases = new[] { "Primary2DAxis" })]
        public Vector2Control joystick { get; private set; }
        public AxisControl trigger { get; private set; }
        [InputControl(aliases = new[] { "Secondary2DAxis" })]
        public Vector2Control touchpad { get; private set; }
        public AxisControl grip { get; private set; }
        public ButtonControl gripPressed { get; private set; }
        [InputControl(aliases = new[] { "Primary" })]
        public ButtonControl menu { get; private set; }
        public ButtonControl joystickClicked { get; private set; }
        public ButtonControl triggerPressed { get; private set; }
        [InputControl(aliases = new[] { "joystickorpadpressed" })]
        public ButtonControl touchpadClicked { get; private set; }
        [InputControl(aliases = new[] { "joystickorpadtouched" })]
        public ButtonControl touchpadTouched { get; private set; }
        public IntegerControl trackingState { get; private set; }
        public ButtonControl isTracked { get; private set; }
        public Vector3Control devicePosition { get; private set; }
        public QuaternionControl deviceRotation { get; private set; }
        public Vector3Control deviceVelocity { get; private set; }
        public Vector3Control deviceAngularVelocity { get; private set; }

        protected override void FinishSetup(InputDeviceBuilder builder)
        {
            if (builder == null)
                throw new System.ArgumentNullException(nameof(builder));

            base.FinishSetup(builder);

            joystick = builder.GetControl<Vector2Control>("joystick");
            trigger = builder.GetControl<AxisControl>("trigger");
            touchpad = builder.GetControl<Vector2Control>("touchpad");
            grip = builder.GetControl<AxisControl>("grip");
            gripPressed = builder.GetControl<ButtonControl>("gripPressed");
            menu = builder.GetControl<ButtonControl>("menu");
            joystickClicked = builder.GetControl<ButtonControl>("joystickClicked");
            triggerPressed = builder.GetControl<ButtonControl>("triggerPressed");
            touchpadClicked = builder.GetControl<ButtonControl>("touchpadClicked");
            touchpadTouched = builder.GetControl<ButtonControl>("touchPadTouched");
            trackingState = builder.GetControl<IntegerControl>("trackingState");
            isTracked = builder.GetControl<ButtonControl>("isTracked");
            devicePosition = builder.GetControl<Vector3Control>("devicePosition");
            deviceRotation = builder.GetControl<QuaternionControl>("deviceRotation");
            deviceVelocity = builder.GetControl<Vector3Control>("deviceVelocity");
            deviceAngularVelocity = builder.GetControl<Vector3Control>("deviceAngularVelocity");
        }
    }
}
