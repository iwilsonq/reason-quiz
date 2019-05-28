[@react.component]
let make = (~children, ~onSubmit) =>
  <form className="bg-white shadow-md rounded px-8 pt-6 pb-8 mb-4" onSubmit>
    children
  </form>;

module Input = {
  [@react.component]
  let make = (~id, ~type_, ~onChange, ~value, ~placeholder="") =>
    <input
      id
      className="appearance-none border rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
      type_
      placeholder
      onChange
      value
    />;
};