import { Slider, styled } from "@material-ui/core"
import {
  Streamlit,
  StreamlitComponentBase,
  withStreamlitConnection,
} from "streamlit-component-lib"
import React, { ReactNode } from "react"


interface State {
  selectedIndex: number
  isFocused: boolean
}

function createMarks(labels: string[]): any[] {
  return labels.map((label, index) => { return { value: index, label } })
}

/**
 * This is a React-based component template. The `render()` function is called
 * automatically when your component should be re-rendered.
 */
class DiscreteSlider extends StreamlitComponentBase<State> {
  public state = { selectedIndex: 1, isFocused: false }
  public options = this.props.args["options"]

  public render = (): ReactNode => {

    const vMargin = 7
    const hMargin = 20

    const StyledSlider = styled(Slider)({
      margin: `${vMargin}px ${hMargin}px`,
      width: this.props.width - (hMargin * 2)
    });


    return (
      <StyledSlider
        defaultValue={this.state.selectedIndex}
        min={0}
        max={this.options.length - 1}
        aria-labelledby="discrete-slider-restrict"
        step={null}
        valueLabelDisplay="off"
        marks={createMarks(this.options)}
        onFocus={this._onFocus}
        onBlur={this._onBlur}
        onChangeCommitted={(event, value): void => {
          const index = Number(value)
          const selectedIndex = this.options[index]
          this.setState(
            prevState => ({ selectedIndex: index }),
            () => Streamlit.setComponentValue(selectedIndex)
          )
        }}
        disabled={this.props.disabled} />
    )
  }

  /** Focus handler */
  private _onFocus = (): void => {
    this.setState({ isFocused: true })
  }

  /** Blur handler */
  private _onBlur = (): void => {
    this.setState({ isFocused: false })
  }

}

// "withStreamlitConnection" is a wrapper function. It bootstraps the
// connection between your component and the Streamlit app, and handles
// passing arguments from Python -> Component.
//
// You don't need to edit withStreamlitConnection (but you're welcome to!).
export default withStreamlitConnection(DiscreteSlider)
