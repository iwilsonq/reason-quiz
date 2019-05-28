let str = React.string;

module Heading = {
  [@react.component]
  let make = (~children) => {
    <h1 className="text-black-700 text-xl font-semibold"> {children |> str} </h1>;
  };
};

module Span = {
  [@react.component]
  let make = (~uppercase=false, ~children) => {
    let className =
      "text-gray-500 "
      ++ (uppercase ? "uppercase text-xs font-bold" : "text-base");
    <span className> {children |> str} </span>;
  };
};

[@react.component]
let make = (~children) => {
  <p className="text-black-700 text-base"> {children |> str} </p>;
};